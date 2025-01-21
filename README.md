# Get Next Line (GNL) - دليل المستخدم 🚀

## شنو هو GNL؟ 
هادا مشروع كيعاونك تقرا سطر بسطر من شي ملف. كيرجع ليك السطر كامل حتى يوصل ل '\n' أو نهاية الملف.

## شنو خاصني نتعلم قبل ما نبدا؟ 📚
1. كيفاش كيخدم **malloc** و **free**
2. المؤشرات (Pointers)
3. المتغيرات الستاتيك (Static Variables)
4. الفونكسيون ديال القراية **read()**
5. القوائم المتسلسلة (إلا بغيتي دير البونيس)

## الفايلات لي غادي تحتاج 📂
```
get_next_line.c
get_next_line.h
get_next_line_utils.c
```

## الفونكسيون الرئيسية 🔍
```c
char *get_next_line(int fd);
```

### المدخلات:
- `fd`: رقم الملف (file descriptor) لي بغيتي تقرا منو

### المخرجات:
- السطر لي تقرا متضمن '\n'
- `NULL` إلا كان شي مشكل أو وصلنا لأخر الملف

## كيفاش كتخدم؟ 🛠️

### 1. التجميع:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

### 2. مثال بسيط:
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## نصائح مهمة 💡

1. **الميموار**: 
   - ما تنساش تحرر كل سطر من بعد ما تكمل معاه
   - تأكد ما كاينش تسريب ديال الميموار (memory leaks)

2. **BUFFER_SIZE**:
   - يمكن ليك تغير الحجم ديالو فوقت التجميع
   - جرب أحجام مختلفة (1, 42, 10000000)

3. **الإختبارات**:
   - جرب مع ملفات فارغة
   - جرب مع سطور طوال بزاف
   - جرب مع file descriptors غالطين

## المشاكل المعروفة وحلولها 🔧

1. **تسريب الميموار**:
   - تأكد من free() لكل malloc()
   - استعمل valgrind باش تشوف المشاكل

2. **مشاكل فالقراية**:
   - تحقق من قيمة BUFFER_SIZE
   - تأكد من حقوق القراية ديال الملف

3. **الأداء**:
   - اختار BUFFER_SIZE مناسب
   - تجنب النسخ الزايد ديال الداتا

## البونيس (إختياري) ⭐
1. استعمل القوائم المتسلسلة
2. خدم مع file descriptors متعددين فنفس الوقت

## أدوات مفيدة 🛠️
- valgrind: للبحث على تسريب الميموار
- gdb: للديباغينغ
- lldb: للديباغينغ على ماك

## المراجع المهمة 📚
1. [Manual ديال read()](https://man7.org/linux/man-pages/man2/read.2.html)
2. [معلومات على File Descriptors](https://en.wikipedia.org/wiki/File_descriptor)
3. [شرح Static Variables](https://en.wikipedia.org/wiki/Static_variable)
## شرح Flowchart 📊

هاد Flowchart كيوضح المسار الكامل ديال `get_next_line`:

![Logo](https://github.com/elbardii/get_next_line/blob/master/GNL.drawio.svg)
