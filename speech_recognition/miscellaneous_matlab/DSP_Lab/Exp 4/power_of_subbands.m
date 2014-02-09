function p = power_of_subbands(A)

size_size=size(A);

p = zeros(size_size(1),1);

size_size = size(A);
number_of_filters = size_size(1);

for n = 1:number_of_filters
    p(n) = sum(abs(fft(A(n,:)).^2))/length(A(n,:));
end
end