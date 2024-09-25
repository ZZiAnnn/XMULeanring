function result = my_conv(f, w)

    [f_height, f_width] = size(f);
    [w_height, w_width] = size(w);
    

    result_height = f_height - w_height + 1;
    result_width = f_width - w_width + 1;

    %右边和底部进行填充
    padded_f = padarray(f, [w_height-1, w_width-1], 'post');

    result = zeros(result_height, result_width,'int16');
    kernel = zeros(w_height,w_width,'int16');

    for i = 1:w_height
        for j = 1:w_width
            kernel(i, j) =  w(w_height - i + 1, w_width - j + 1);
        end
    end

    for i = 1:f_height
        for j = 1:f_width
            region = padded_f(i:i+w_height-1, j:j+w_width-1);
            result(i, j) = sum(region(:) .* kernel(:));
        end
    end
end
