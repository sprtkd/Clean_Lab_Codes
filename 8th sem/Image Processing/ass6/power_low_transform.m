function [ new_img ] = power_low_transform( img, c, gamma )
[row,col,channels]=size(img);

new_img = double(zeros(row,col,1));

for i=1:row
    for j=1:col
       new_img(i,j) = c*(double(img(i,j)) ^ gamma);
       if new_img(i,j) > 255
           new_img(i,j) = 255;
       end
    end
end

new_img = uint8(new_img);
end

