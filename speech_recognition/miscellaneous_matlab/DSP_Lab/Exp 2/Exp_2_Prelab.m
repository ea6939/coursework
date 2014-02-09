T = 10000;
fs = 10000;
f = 0:1/fs:1-1/fs;

high = ones(5000, 1);
low = zeros(5000, 1);
rectangle = cat(1, high, low)';
S = fft(rectangle);

G = (2/T)*abs(S).^2.*(1-cos(3*pi*f*T));

subplot(2,1,1), plot(abs(S));
subplot(2,1,2), plot(G);
axis([0 20 0 5000]);