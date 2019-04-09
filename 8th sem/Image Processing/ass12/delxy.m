function [ new_img ] = delxy( img )
[row,col,channels]=size(img);
delx = double(zeros(row,col,1));
dely = double(zeros(row,col,1));
new_img = double(zeros(row,col,1));

for i=1:row
    for j=1:col-1
        delx(i,j) = img(i,j) - img(i,j+1);
    end
end

for i=1:row-1
    for j=1:col
        dely(i,j) = img(i,j) - img(i+1,j);
    end
end

for i=1:row
    for j=1:col
        new_img(i,j) = abs(delx(i,j)) + abs(delx(i,j));
    end
end

new_img = uint8(new_img);
end

