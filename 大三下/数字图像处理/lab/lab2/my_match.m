function[]=my_match(source_img,target_img)
    source_image=imread(source_img);
    target_image=imread(target_img);

    [M1,N1]=size(source_image);
    [M2,N2]=size(target_image);

    source_hist=imhist(source_image);
    target_hist=imhist(target_image);
    
    source_cdf = cumsum(source_hist) / (M1*N1);
    target_cdf = cumsum(target_hist) / (M2*N2);

    map=zeros(256,1,"uint8");
    for i=1:256
        [~,idx]=min(abs(source_cdf(i)-target_cdf));
        map(i)=idx-1;
    end

    matched_image=map(source_image+1);
    figure;
    subplot(231); imshow(source_image); title('原始');
    subplot(232); imshow(target_image); title('匹配图');
    subplot(233); imshow(matched_image); title('匹配后的新图');

    subplot(234); imhist(source_image,64); title('原始');
    subplot(235); imhist(target_image,64); title('匹配图');
    subplot(236); imhist(matched_image,64); title('匹配后的新图');
end