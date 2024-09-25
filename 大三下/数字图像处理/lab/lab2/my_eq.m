function[] =my_eq(source_img)
    img=imread(source_img);
    
    [M,N]=size(img);
    
    pixel_counts=zeros(256,1);
    for i=1:M
        for j=1:N
            pixel_counts(img(i,j)+1)=pixel_counts(img(i,j)+1)+1;
        end
    end
    
    cdf=cumsum(pixel_counts)/(M*N);
    
    target_img=zeros(M,N);
    for i=1:M
        for j=1:N
            target_img(i,j)=round(cdf(img(i,j)+1)*255);
        end
    end
    
    figure(1)
    subplot(121),imshow(uint8(img)),title('原始图像');
    subplot(122),imshow(uint8(target_img)),title('直方图均衡后的图像');
    
    figure(2)
    
    subplot(121),imhist(uint8(img),64),title('原始直方图');
    xlim([0, 250]);
    ylim([0, 4e4]);

    subplot(122),imhist(uint8(target_img),64),title('处理后的直方图');
    xlim([0, 250]);
    ylim([0, 2.5e4]);
end
