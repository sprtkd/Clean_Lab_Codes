function [ new_img ] = highboost( img, A )
[row,col,channels]=size(img);
new_img = double(zeros(row,col,1));

kernel= double([-1 -1 -1 ; -1 A+8 -1; -1 -1 -1]);

for i=2:row-1
    for j=2:col-1
        extracted = double(img((i-1):(i+1),(j-1):(j+1)));
        conv = extracted.*kernel;
        new_img(i,j) = sum(conv(:));
    end
end

new_img = uint8(new_img);
end

