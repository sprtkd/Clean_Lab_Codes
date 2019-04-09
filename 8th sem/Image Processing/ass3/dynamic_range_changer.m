function [ new_img ] = dynamic_range_changer( img, c, d )
[row,col,channels]=size(img);
b = max(img(:));
a = min(img(:));
new_img = double(zeros(row,col,1));
x=double(d-c);
y=double(b-a);
z=x/y;
for i=1:row
    for j=1:col
        new_img(i,j) = ((img(i,j)-a)*z)+c;

    end
end

new_img = uint8(new_img);
end