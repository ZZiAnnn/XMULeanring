function my_Laplacian()
    image = imread('building.tif');
    Laplacian_mask = [
        0,  1, 0;
        1, -4, 1;
        0,  1, 0;
        ];

    bound = my_conv(int16(image), int16(Laplacian_mask));
    result = int16(image) + bound;

    figure(1)
    subplot(131),imshow(uint8(image)),title('原始');
    subplot(132),imshow(uint8(bound)),title('轮廓');
    subplot(133),imshow(uint8(result)),title('拉普拉斯算法锐化后');
end
