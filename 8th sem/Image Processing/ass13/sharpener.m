function [ new_img ] = sharpener( img )
[row,col,channels]=size(img);
delx = double(zeros(row,col,1));
dely = double(zeros(row,col,1));
new_img = double(zeros(row,col,1));

kernel_delx = double([1 2 1; 0 0 0; -1 -2 -1]);
kernel_dely = double([1 0 -1; 2 0 -2; 1 0 -1]);

for i=2:row-1
    for j=2:col-1
        extracted = double(img((i-1):(i+1),(j-1):(j+1)));
        conv =(extracted.*kernel_delx);
        delx(i,j) = sum(conv(:));
    end
end


for i=2:row-1
    for j=2:col-1
        extracted = double(img((i-1):(i+1),(j-1):(j+1)));
        conv =(extracted.*kernel_dely);
        dely(i,j) = sum(conv(:));
    end
end

for i=1:row
    for j=1:col
        new_img(i,j) = abs(delx(i,j)) + abs(delx(i,j));
    end
end

new_img = uint8(new_img);
end

