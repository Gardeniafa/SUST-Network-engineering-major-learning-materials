from django.contrib import admin
from . import models


# Register your models here.
# @admin.register(models.Department)
# class DepartmentAdmin(admin.ModelAdmin):
#     pass
#
#
# @admin.register(models.Author)
# class AuthorAdmin(admin.ModelAdmin):
#     pass


@admin.register(models.Passage)
class PassageAdmin(admin.ModelAdmin):
    pass

# @admin.register(models.Image)
# class ImageAdmin(admin.ModelAdmin):
#     ...
