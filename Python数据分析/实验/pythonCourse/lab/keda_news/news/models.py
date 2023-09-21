from django.db import models
from news import utils
import uuid


class Passage(models.Model):
    passage_id = models.CharField(max_length=32, default='undefined', primary_key=True, editable=False)
    number = models.IntegerField(default=-1, auto_created=True)
    # author_id: int = models.ForeignKey(Author, on_delete=models.CASCADE)
    # authors = models.ManyToManyField('Author')
    author = models.CharField(max_length=32, default='undefined')
    title: str = models.CharField(max_length=128)
    content = models.TextField()
    time = models.DateTimeField(auto_now=True)

    def __str__(self):
        return f'{self.title} - {self.author} |  {self.time}'

    def save(self, *args, **kwargs):
        if self._state.adding:
            max_value = Passage.objects.all().aggregate(max=models.Max("number"))["max"] or 0
            self.number = max_value + 1
        super().save(*args, **kwargs)


class Image(models.Model):
    img_uuid = models.CharField(primary_key=True, default=uuid.uuid4, editable=False, max_length=64)
    type = models.CharField(max_length=32, default='normal')
    img = models.ImageField(upload_to=utils.ModelUtils.gen_save_img_location)
    name = models.CharField(max_length=512, default='undefined')
    hash_md5 = models.CharField(max_length=128, default='undefined')
    time = models.DateTimeField(null=True, auto_now=True)

    def save(self, *args, **kwargs):
        if not self.img.name.startswith('http'):
            self.img.name = f'{self.img_uuid}.{self.img.name.split(".")[-1]}'
            # print('fuck the img name is: ', self.img.name)
        super(Image, self).save(*args, **kwargs)
