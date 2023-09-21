from django import template


def max_len_str(string: str, length: int) -> str:
    if length <= 0 or len(string) <= length:
        return string
    else:
        return string[:length] + '...'


register = template.Library()
register.filter(max_len_str)
