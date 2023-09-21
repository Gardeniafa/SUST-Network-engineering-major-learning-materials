import datetime
from django.http import HttpRequest
import json
import hashlib
from functools import partial


def __current_date_str__():
    now = datetime.datetime.now()
    date_str = now.strftime("%Y%m%d")
    return date_str


class ModelUtils:
    @staticmethod
    def gen_save_img_location(*args):
        if args[0].type.replace(' ', '').replace('\\', '_').replace('/', '-').lower() in ('', ' ', 'normal'):
            s = f'static\\images\\normal\\{__current_date_str__()}\\{args[-1]}'
        else:
            s = f'static\\images\\{args[0].type}\\{__current_date_str__()}\\{args[-1]}'
        print('fuck the dir is: ', s)
        return s


class RequestUtils:
    @staticmethod
    def get_value(request: HttpRequest, key: str, ord_method='POST'):
        if request.content_type in ('application/x-www-form-urlencoded', 'multipart/form-data'):
            try:
                method = request.method
                if method in ('POST', ):
                    return request.POST[key]
                elif method in ('GET', ):
                    return request.GET[key]
                else:
                    return None
            except Exception:
                return None
        elif request.content_type in ('application/json', ):
            try:
                method = request.method
                if method != ord_method:
                    return None
                data = json.loads(request.body.decode())
                return data[key]
            except Exception:
                return None
        else:
            return None

    @staticmethod
    def md5(request_file, block_size=65536):
        m = hashlib.md5()
        for item in iter(partial(request_file.read, block_size), b''):
            m.update(item)
        str_md5 = m.hexdigest()
        return str_md5
