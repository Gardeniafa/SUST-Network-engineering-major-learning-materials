from django.shortcuts import render
from django.http import HttpResponsePermanentRedirect, HttpRequest, HttpResponse, JsonResponse
from . import models
from uuid import uuid4
from django.contrib import auth
from news.utils import RequestUtils
from django.db.models import Q


# Create your views here.
def default(request: HttpRequest):
    return HttpResponsePermanentRedirect('getNewsList')


def test(request: HttpRequest):
    li = RequestUtils.get_value(request, 'title')
    if not li:
        return JsonResponse(content_type='application/json', data={
            'status': 'failed',
            'message': 'bad request'
        }, status=400)
    return HttpResponse('success')


class ImageView:
    @staticmethod
    def add(request: HttpRequest):
        image = None
        if request.method.upper() in ['POST']:
            img_fingerprint = RequestUtils.md5(request.FILES['img'], )
            try:
                img_db_query = models.Image.objects.get(hash_md5=img_fingerprint)
                if img_db_query:
                    image = img_db_query
                else:
                    raise
            except Exception:
                file_name = request.FILES['img'].name
                ran_uid = uuid4()
                try:
                    type_ = request.POST['type']
                    image = models.Image(img_uuid=ran_uid, img=request.FILES['img'], name=file_name, type=type_, hash_md5=img_fingerprint)
                except Exception:
                    image = models.Image(img_uuid=ran_uid, img=request.FILES['img'], name=file_name, hash_md5=img_fingerprint)
                image.save()
            finally:
                try:
                    if request.POST['api'] in ('true', True):
                        response = JsonResponse({
                            'status': 'success',
                            'source': f'{image.img.url}'
                        })
                        response['access-control-allow-origin'] = '*'
                        return response
                except Exception:
                    return render(request, '404.html')
        if request.method.upper() in ['OPTIONS']:
            response = HttpResponse()
            response['Access-Control-Allow-Origin'] = '*'
            response['Access-Control-Allow-Methods'] = 'POST'
            response['Access-Control-Max-Age'] = '86400'
            response['Access-Control-Allow-Headers'] = 'Content-Type'
            return response
        return render(request, '404.html')

    @staticmethod
    def get(request: HttpRequest, uuid: str):
        try:
            image = models.Image.objects.filter(img_uuid=uuid)
            return HttpResponsePermanentRedirect(image[0].img.url)
        except Exception:
            return JsonResponse({
                'status': 'failed',
                'message': f'could not found image at {uuid}'
            }, status=404)


class LoginView:
    @staticmethod
    def login_method(request: HttpRequest):
        if request.method.upper() in ('GET',):
            try:
                next_page = request.GET['next']
            except Exception:
                return render(request, '404.html')
            if request.user.is_authenticated:
                return HttpResponsePermanentRedirect(redirect_to=next_page)
            return render(request, 'login.html', {
                'next_page': next_page
            })
        elif request.method.upper() in ('POST',):
            username = request.POST['user']
            pwd = request.POST['pwd']
            next_page = request.POST['next_page']
            user = auth.authenticate(request, username=username, password=pwd)
            if user is not None:
                if user.groups.filter(Q(name='admin') | Q(name='author')).exists():
                    auth.login(request, user)
                    return HttpResponsePermanentRedirect(redirect_to=next_page)
                else:
                    return render(request, 'login.html', {
                        'next_page': next_page,
                        'error': f'{username} 不在是一个有效的新闻作者用户！'
                    })
            else:
                return render(request, f'login.html', {
                    'next_page': next_page,
                    'error': '用户名或密码错误！'
                })
        else:
            return JsonResponse({
                'status': 'fuck the method'
            }, status=404)

    @staticmethod
    def logout(request: HttpRequest):
        user = request.user
        if user.is_authenticated:
            auth.logout(request)
        return HttpResponsePermanentRedirect(redirect_to='/')


class NewsView:
    @staticmethod
    def add_news(request: HttpRequest):
        user = request.user
        if user.is_authenticated:
            if request.method.upper() in ('POST',):
                try:
                    author_name = user.username
                    content = RequestUtils.get_value(request, 'content')
                    title = RequestUtils.get_value(request, 'title')
                    if content is None or title is None:
                        raise
                    passage_id = RequestUtils.get_value(request, 'passage_id')
                except Exception:
                    return JsonResponse({
                        'status': 'failed',
                        'message': 'wrong params'
                    }, status=400)
                else:
                    if passage_id is None:
                        try:
                            passage_id = str(uuid4())[:32]
                            passage = models.Passage.objects.create(passage_id=passage_id, title=title, author=author_name,
                                                                    content=content)
                            passage.save()
                            return JsonResponse({
                                'status': 'success',
                                'passage_id': passage_id
                            })
                        except Exception:
                            return JsonResponse({
                                'status': 'failed',
                                'message': 'add passage internal error'
                            }, status=500)
                    else:
                        try:
                            passage = models.Passage.objects.get(passage_id=passage_id)
                            passage.content = content
                            passage.title = title
                            passage.save()
                            return JsonResponse({
                                'status': 'success',
                                'passage_id': passage_id
                            })
                        except Exception:
                            return JsonResponse({
                                'status': 'failed',
                                'message': 'internal error'
                            }, status=500)

            elif request.method.upper() in ('GET',):
                return render(request, 'add-news.html', {
                    'login_author': user.username,

                })
            elif request.method.upper() in ('OPTIONS',):
                response = HttpResponse()
                response['Access-Control-Allow-Origin'] = '*'
                response['Access-Control-Allow-Methods'] = 'POST'
                response['Access-Control-Max-Age'] = '86400'
                response['Access-Control-Allow-Headers'] = 'Content-Type'
                return response
            else:
                return HttpResponse(status=400, content_type='application/json', content={
                    'status': 'failed',
                    'msg': 'unsupported request method'
                })
        else:
            return HttpResponsePermanentRedirect(redirect_to='login?next=addNews')

    @staticmethod
    def get_news_list(request: HttpRequest):
        if request.method in ('GET', ):
            try:
                page_policy = str(request.GET['page'])
                page, nums = map(int, page_policy.split('.'))
            except Exception:
                return HttpResponsePermanentRedirect(redirect_to='/getNewsList?page=1.10')
            else:
                total_news = models.Passage.objects.count()
                total_pages = -1 * (-1 * total_news // nums)
                if 0 < total_pages < page or page <= 0:
                    return HttpResponse('there is no such more news', status=404)
                else:
                    find_news = models.Passage.objects.filter(number__gte=(page-1)*nums+1, number__lte=page*nums)
                    return render(request, 'news-list-pages.html', {
                        'passages': find_news,
                        'previous_enable': page != 1,
                        'next_enable': page < total_pages,
                        'total_pages': total_pages,
                        'page': page,
                        'next_page_num': page if page >= total_pages else page+1,
                        'previous_page_num': 1 if page == 1 else page - 1,
                        'page_num': nums
                    })
        else:
            return HttpResponsePermanentRedirect(redirect_to='/getNewsList?page=1.10')

    @staticmethod
    def get_news_by_id(request: HttpRequest, news_id: str):
        news_detail = models.Passage.objects.filter(passage_id=news_id)
        use_as_api = RequestUtils.get_value(request, 'api')
        if use_as_api is not None:
            if news_detail:
                return JsonResponse({
                    'status': 'success',
                    'title': news_detail[0].title,
                    'content': news_detail[0].content
                })
            else:
                return JsonResponse({
                    'status': 'failed',
                    'message': 'could not find passage ' + news_id
                }, status=404)
        if news_detail:
            return render(request, 'news.html', {
                'news': news_detail[0]
            })
        else:
            return render(request, '404.html', {

            })

    @staticmethod
    def get_news_list_by_login_user(request: HttpRequest):
        if not request.user.is_authenticated:
            return JsonResponse({
                'status': 'failed',
                'message': 'unauthorized request'
            }, status=403)
        else:
            passages = models.Passage.objects.filter(author=request.user.username)
            res = []
            for i in passages:
                res.append({
                    'passage_id': i.passage_id,
                    'title': i.title,
                    'content': i.content,
                    'time': i.time
                })
            return JsonResponse({
                'status': 'success',
                'count': len(res),
                'passages': res
            })

    @staticmethod
    def update_news(request: HttpRequest):
        if request.user.is_authenticated and request.user.groups.filter(Q(name='admin') | Q(name='author')).exists():
            return render(request, 'change-news.html', {
                'login_author': request.user.username,

            })
        else:
            return HttpResponsePermanentRedirect(redirect_to='login?next=changePassages')

    @staticmethod
    def delete_news_by_id(request: HttpRequest):
        if not request.user.is_authenticated:
            return JsonResponse({
                'status': 'failed',
                'message': 'unauthorized request'
            }, status=403)
        else:
            passage_id = RequestUtils.get_value(request, 'passage_id')
            if passage_id is None:
                return JsonResponse({
                    'status': 'failed',
                    'message': 'param error'
                }, status=400)
            else:
                try:
                    passage = models.Passage.objects.get(passage_id=passage_id)
                except Exception:
                    passage = None
                if passage:
                    passage.delete()
                    return JsonResponse({
                        'status': 'success',
                    })
                else:
                    return JsonResponse({
                        'status': 'failed',
                        'message': 'passage does not exist'
                    })
