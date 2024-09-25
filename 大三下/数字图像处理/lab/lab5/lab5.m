function lab5 ()
    image = imread('./image.png');
    watermark = imread('./xmu-logo.png');

    
    watermark = imresize(watermark,[size(image, 1), size(image, 2)]);
    image = double(image);
    watermark = double(watermark);

    %添加水印
    alpha = 0.0001;
    watermarked_image = zeros(size(image));
    for channel = 1:3
        
        dct_image_channel = dct2(image(:,:,channel));
        watermark_channel = watermark(:,:,channel);

        watermarked_dct_channel = dct_image_channel .* (1 + alpha * watermark_channel);
        watermarked_image(:,:,channel) = idct2(watermarked_dct_channel);
        
    end
    imwrite(uint8(watermarked_image),'./out_image.png');
  %  watermarked_image = imread('./out_image.png');
    %提取水印

    extract_watermark = zeros(size(image));
    for channel = 1:3        
        dct_watermarked_image = dct2(watermarked_image(:,:,channel));
        dct_image_channel = dct2(image(:,:,channel));
        extract_watermark(:,:,channel) = (dct_watermarked_image ./ dct_image_channel - 1) / alpha;    
    end
    figure;
    subplot(2,2,1);imshow(uint8(image));title('载体图像');
    subplot(2,2,2);imshow(uint8(watermark));title('水印图像');
    subplot(2,2,3);imshow(uint8(watermarked_image));title('添加水印后的图像');
    subplot(2,2,4);imshow(uint8(extract_watermark));title('提取出水印');
    
end
