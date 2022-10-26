# picture.bmp-for-c-read
![image](https://github.com/SCU-jackydong/picture.bmp-for-c-read/blob/master/5aea93676865d06cf8ce779e27579e0.jpg)


使用c语言通过库函数fopen， fread和fwrite，去调用内核的open函数，read函数和write函数，通过系统调用完成用户态到内核态的转变。按照bmp图片的存储格式进行读取，并写进新的文件路径，进行显示，
中间对像素点进行二值化处理。

原始图片图下
![image](https://github.com/SCU-jackydong/picture.bmp-for-c-read/blob/master/origin_picture.bmp)

读取并进行二值化处理后的图片显示图下
![image](https://github.com/SCU-jackydong/picture.bmp-for-c-read/blob/master/threthold.bmp)
