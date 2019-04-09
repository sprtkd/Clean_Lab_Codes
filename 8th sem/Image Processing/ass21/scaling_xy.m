function [ new_img ] = scaling_xy( img,mulh,mulv )
[row,col,channels]=size(img);
new_rows = int32(mulv*row);
new_cols = int32(mulh*col);
new_img = double(zeros(new_rows,new_cols,1));
for i=1:row
    for j=1:col
        new_img(int32(i*mulv),int32(j*mulh)) = img(i,j);
    end
end
new_img = uint8(new_img);

end

