function [ neg_img ] = img_neg( img )
[row,col,channels]=size(img);

neg_img = zeros(row,col,1);

for i=1:row
    for j=1:col
        neg_img(i,j) = (255-img(i,j)-1);
    end
end
neg_img = uint8(neg_img);
end

