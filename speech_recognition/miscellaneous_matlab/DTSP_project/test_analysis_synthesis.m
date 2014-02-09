% test analysis_synthesis

% input signal
%X = sin(0.001*(1:15000));
% for d=1:15000
% X(d)=3;
% end
% for d=1:480
% X(d)=0;
% end
% noise=0.1*(randn(size(X)));
% X=X+noise;
% X = wavread('test_noisy.WAV');
% X = wavread('once_upon_a_time.wav');
% X = X + 0.01*randn(size(X));
% X = X';
clear
X = ones([1 20000]);

speech_start=22150;

%parameters needed for choose_strarting_window
T0 = 256;
overlap = 1;
input_signal_length = length(X);

number_of_windows = (input_signal_length/T0)*(1+overlap);
start_of_window = floor((input_signal_length/number_of_windows))*(0:number_of_windows);

%choose the starting window for speech activity
s=choose_starting_window(input_signal_length,number_of_windows,speech_start);

%% apply windows to the input signal
A = window_analysis_256_efficient(X,overlap);

%% fft
for d = 1:length(A(:,1))
    B(d,:) = fft(A(d,:));
end

%% ifft
for d = 1:length(B(:,1))
    pieces(d,:) = ifft(B(d,:));
end

%% add
test_reconstruct = zeros(size(X));
for n = 1:length(pieces(:,1))-1
    test_reconstruct(start_of_window(n)+1:start_of_window(n)+256) = test_reconstruct(start_of_window(n)+1:start_of_window(n)+256) + pieces(n,:);
end

error = test_reconstruct - X;
plot(test_reconstruct)