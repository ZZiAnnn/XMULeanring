function [] = my_ideal()
% 使用DFT、IDFT，以及理想高、低通滤波器，进行频域滤波

% 第1步：读取图像，将大小扩展为2M*2N，并填充0
f = imread('test2.tif');
f = im2double(f);
[M,N] = size(f);
fp=[f zeros(M,N); zeros(M,2*N)];

% 第2步：进行DFT，并将将零频分量移到频谱中心
%F = fftshift(fft2(fp));  % fft2函数：二维快速傅里叶变换
F = fftshift(my_DFT(fp));  % fftshift函数：用于将零频分量移到频谱中心

% 第3步：滤波
% 设计滤波器
u = -N:N-1;
v = -M:M-1;
[U,V] = meshgrid(u,v);       % meshgrid函数：生成矩阵U（V），其元素值等于它所在的列（行） 
D = hypot(U,V);              % hypot函数：求每个元素的平方根，即与频率零点的距离
D0 = 30;                     % 截止频率设置为30
ILPF = mat2gray( D <= D0 );  % 理想低通滤波器
IHPF = mat2gray( D > D0 );   % 理想高通滤波器
% 频域滤波
G1 = F.*ILPF;
G2 = F.*IHPF;
 
% 第4步：还原频谱的位置，进行IDFT，取实部并裁剪
% gp1 = ifft2(fftshift(G1));
gp1 = my_IDFT(fftshift(G1));
% gp2 = ifft2(fftshift(G2));
gp2 = my_IDFT(fftshift(G2));
g1 = real(gp1);    % 取实部
g2 = real(gp2);
g1 = g1(1:M,1:N);  % 裁剪掉填充0的区域
g2 = g2(1:M,1:N);

% 第5步：输出结果
fprintf('输出结果:\n');
figure;
subplot(2,2,1);imshow(f);title('原图');
subplot(2,2,2);imshow(mat2gray(log(1+abs(F))));title('傅里叶频谱');
subplot(2,2,3);imshow(g1);title('理想低通滤波后的图像');
subplot(2,2,4);imshow(g2);title('理想高通滤波后的图像');
end