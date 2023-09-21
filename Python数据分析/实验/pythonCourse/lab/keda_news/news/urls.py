from django.urls import path
from . import views


urlpatterns = [
    path('', views.default),
    path('addImage', views.ImageView.add),
    path('getImage/<str:uuid>', views.ImageView.get),
    path('login', views.LoginView.login_method),
    path('addNews', views.NewsView.add_news),
    path('getNewsList', views.NewsView.get_news_list),
    path('news/<str:news_id>', views.NewsView.get_news_by_id),
    path('logout', views.LoginView.logout),
    path('getAuthorAlbum', views.NewsView.get_news_list_by_login_user),
    path('deletePassage', views.NewsView.delete_news_by_id),
    path('changePassages', views.NewsView.update_news)
]
