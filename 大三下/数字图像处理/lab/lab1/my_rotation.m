function [] =my_rotation(file_name,rotation_degree)
    image=imread(file_name);
    rotated_image=imrotate(image,rotation_degree);
    imwrite(rotated_image,'rotated_image.tif');
    imshow('rotated_image.tif');
end