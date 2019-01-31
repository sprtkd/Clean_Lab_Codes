function [ up_img ] = upsampler( img )
[row,col,channels]=size(img);
new_row = round(row*2);
new_col = round(col*2);

up_img = zeros(new_row,new_col,1);

for i=1:row
    for j=1:col
        new_i=i*2;
        new_j=j*2;
            up_img(new_i,new_j) = img(i,j);
            up_img(new_i-1,new_j) = img(i,j);
            up_img(new_i,new_j-1) = img(i,j);
            up_img(new_i-1,new_j-1) = img(i,j);
    end
end

up_img = uint8(up_img);
end

