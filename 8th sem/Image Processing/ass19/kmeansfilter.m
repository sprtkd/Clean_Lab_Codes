function [ new_img ] = kmeansfilter( img, filter_n, k )
[row,col,channels]=size(img);

adder = round((filter_n - 1)/2);
padded_img = double(zeros(row+(adder*2),col+(adder*2),1));

new_img = double(zeros(row,col,1));

for i=1:row
    for j=1:col
        padded_img(i+adder,j+adder) = img(i,j);
    end
end

for i=1+adder:row+adder
    for j=1+adder:col+adder
        if(mod(filter_n,2)==0)
            extracted = padded_img([(i-adder):(i+adder-1)],[(j-adder):(j+adder-1)]);
        else
            extracted = padded_img([(i-adder):(i+adder)],[(j-adder):(j+adder)]);
        end
        filter_list = extracted(:);
        filter_list = filter_list.';
        padded_img(i,j) = getknnavg(filter_list, padded_img(i,j), k);
    end
end
for i=1:row
    for j=1:col
        new_img(i,j) = padded_img(i+adder,j+adder);
    end
end
new_img = uint8(new_img);
end

