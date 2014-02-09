function A = analysis_bank(x)

A = zeros(32,256 + length(x)-1);
load('filtersCMFB.mat');

for n = 1:32
    A(n,:) = conv(x, H(n,:));
end
end

