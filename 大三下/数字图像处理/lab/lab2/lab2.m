function [] = lab2()

% 读取原灰度图
R = imread('Einstein.tif');

% 直方图均衡化
S = histeq(R);

figure(1)
% uint8函数：把参数转换为无符号数
subplot(121),imshow(uint8(R)),title('原始图像');
subplot(122),imshow(uint8(S)),title('直方图均衡后的图像');

figure(2)
% imhist函数：显示图像的灰度直方图
subplot(121),imhist(R,64),title('原始直方图');
subplot(122),imhist(S,64),title('处理后的直方图');

end

