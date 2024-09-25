function my_blur()
    f = imread('cover.tif');

    f = im2double(f);
    [M, N] = size(f);

    padM = M / 2;  % 垂直方向上扩展的行数
    padN = N / 2;  % 水平方向上扩展的列数

    fp = padarray(f, [padM padN], 'symmetric', 'both');

    F = fftshift(fft2(fp));  

    a = 0.05; b = 0.015; T = 1;

    u = -N :N - 1;
    v = -M :M - 1;
    [U, V] = meshgrid(u, v);

    s = pi * (U * a + V * b);

    H = T ./ s .* sin(s) .* exp(-1j * s);
    H(s == 0) = T;

    G = H .* F;

    g = real(ifft2(fftshift(G)));
    g = g(M/2:M * 3 / 2, N / 2 :N *3/2);
    g = mat2gray(g);
    f_noise = imnoise(f, 'gaussian', 0, 0.01);
    g_noise = imnoise(g, 'gaussian', 0, 0.01);
    
    figure;
    subplot(2,2,1);imshow(f);title('原始图像');
    subplot(2,2,2);imshow(g);title('运动模糊图像');
    subplot(2,2,3);imshow(f_noise);title('添加高斯噪声的图像');
    subplot(2,2,4);imshow(g_noise);title('模糊且加噪的图像');
end

