function B = upsample_bank(Y)

size_size = size(Y);
size_size(2) = ceil(size_size(2)*size_size(1));
B = zeros(size_size);

for n = 1:size_size(1)
    B(n,:) = upsample(Y(n,:),size_size(1));
end
end