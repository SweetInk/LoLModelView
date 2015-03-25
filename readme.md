#LoL model viewer for mac
origin:http://git.oschina.net/lyricc/LolView/tree/master

#skn mesh

#texture format
TGA,DDS
主要参考了官方文档，Unity3D支持的图形文件格式有 PSD, TIFF, JPG, TGA, PNG, GIF, BMP, IFF, PICT（但根据本人的亲手测试，Unity3D对高压缩游戏贴图DDS是具有良好的解析功能的，但DDS具体也分很多格式类型，我仅对游戏中提取出的DDS进行了测试）。
PSD中层在导入Unity之后将会自动合并，但原PSD文件的层则作为保留，不必介意在PSD里面存放有多个图层。
纹理尺寸是一个重点注意事项，因为非2的幂次尺寸纹理用于GUI纹理时使用会非常好，然而，在其他方面，该纹理将被转化为一个非压缩的RGBA32位格式，这会占用更多的显存，并且大大降低加载速度。但非2的幂次尺寸纹理可以在导入设置中使用Scale NonPower2 Sizes Up将非2的幂次纹理资源放大到2的幂次。这样可以让该图形被当作其他2的幂次尺寸纹理那样使用，被压缩之后占用较小的显存空间，并有较快的加载速度！
还有作为性能的考虑，模型贴图要尽量使用Mip Maps。使用该Mip maps将多使用33%的内存，但能带来很大的性能上的优势。距离相机较远的物体将使用较小的纹理。
最后在非地面和地板模型对象上，尽量不要使用Anisotropic filtering。

#gl draw
红宝书
Dave Shreiner, Graham Sellers, John M. Kessenich and Bill M. Licea-Kane. 2013. OpenGL Programming Guide: The Official Guide to Learning OpenGL, Version 4.3 (8th Edition). Addison-Wesley Professional. ISBN 978-0321773036.

橙宝书
Randi J. Rost, Bill M. Licea-Kane, Dan Ginsburg, John M. Kessenich, Barthold Lichtenbelt, Hugh Malan and Mike Weiblen. 2009. OpenGL Shading Language (3rd Edition). Addison-Wesley Professional. ISBN 978-0321637635

渲染OBJ格式文件（无动画）
http://www.cnblogs.com/zhouxin/p/3453809.html
http://www.cnblogs.com/antai/archive/2010/01/06/1640488.html
http://blog.csdn.net/caca001/article/details/5207597
FBX ！！！
http://en.wikipedia.org/wiki/Category:3D_graphics_file_formats
http://en.wikipedia.org/wiki/FBX
RAW动画数据是怎么样的一个存在？？？

法线贴图：
贴图数据会在pixel shader内可编程处理。
纹理贴图_____> pixel shader > 根据法线和纹理数据及光照->使平面上的Pixel具有3d感。
法线贴图

github的contribution时间线图，可以在上面画个图哦。画点啥呢？

https://code.google.com/p/recombination-3d-4-on-the-beam/ 很有意思