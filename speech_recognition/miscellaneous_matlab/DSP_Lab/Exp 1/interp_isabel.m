t = 1.1;
X = 2:2:1000;
A = 0;
for k = 1:1:length(X)
    A = A + X(k) * (sin(pi*(t-k)))/(pi*(t-k));
end
