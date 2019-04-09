function [ new_img ] = gray_slicer( img, c, d )
[row,col,channels]=size(img);

new_img = zeros(row,col,1);

for i=1:row
    for j=1:col
        if img(i,j) >= c && img(i,j) <= d
            new_img(i,j)=255;
        else
            new_img(i,j)=0;
        end
    end
end

new_img = uint8(new_img);
end