function [ new_img ] = rotate_theta( img, theta )
[row,col,channels]=size(img);
new_img = double(zeros(row,col,1));
cos_theta = cosd(theta);
sin_theta = sind(theta);
for i=1:row
    for j=1:col
        new_i = int32((i*cos_theta)-(j*sin_theta));
        new_j = int32((i*sin_theta)+(j*cos_theta));
        if(new_i>1 && new_j>1)
            new_img(new_i,new_j) = img(i,j);
        end
    end
end
new_img = uint8(new_img);
end

