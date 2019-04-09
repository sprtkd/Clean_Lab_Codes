function [ new_img ] = translate_xy( img, delx,dely )
[row,col,channels]=size(img);
new_img = double(zeros(row,col,1));
for i=1:row
    for j=1:col
        new_i=i-dely;
        new_j=j+delx;
        if new_i<1
            new_i=row+new_i;
        end
        if new_j>col
            new_j=new_j-col;
        end
        new_img(new_i,new_j) = img(i,j);
    end
end
new_img = uint8(new_img);
end

