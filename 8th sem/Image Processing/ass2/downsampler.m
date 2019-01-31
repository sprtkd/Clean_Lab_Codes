function [ down_img ] = downsampler( img )
[row,col,channels]=size(img);
new_row = round(row/2);
new_col = round(col/2);

down_img = zeros(new_row,new_col,1);

for i=1:row
    for j=1:col
        if mod(i,2)==0 && mod(j,2)==0
            new_i = (i/2);
            new_j = (j/2);
            down_img(new_i,new_j) = img(i,j);
        end
    end
end
down_img = uint8(down_img);
end

