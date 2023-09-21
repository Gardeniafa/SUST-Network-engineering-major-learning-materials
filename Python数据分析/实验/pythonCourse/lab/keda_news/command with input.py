import os


count = 0
while True:
    count += 1
    cmd = input(f'In[{count:02n}]>')
    if not cmd.split() or cmd.lower() in ('exit', 'end', 'fuck', 'q'):
        print('Bye.')
        break
    else:
        try:
            os.system(f'python manage.py {cmd}')
        except Exception as e:
            print('error occurs: \n', e)
