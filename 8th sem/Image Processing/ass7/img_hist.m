function [pixelset ] = img_hist( img )
[row,col,channels]=size(img);

pixelset = zeros(256,1);

for i=1:row
    for j=1:col
        pos = img(i,j)+1;
        pixelset(pos) = pixelset(pos) + 1;
    end
end

bar((0:255),pixelset)
end

