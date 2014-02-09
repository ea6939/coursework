function Xhat = remove_noise_main(X, speech_start)

%parameters needed for choose_starting_window
T0 = 256;
overlap = 2;
input_signal_length = length(X);

number_of_windows = (input_signal_length/T0)*(1+overlap);
start_of_window = floor((input_signal_length/number_of_windows)*(0:number_of_windows-1));

%choose the starting window for speech activity
s=choose_starting_window(input_signal_length,number_of_windows,speech_start);

%% apply windows to the input signal
A = window_analysis_256_efficient(X,overlap);

%% fft
for d = 1:length(A(:,1))
    B(d,:) = fft(A(d,:));
end

%compute the average noise here
%find a way to compute efficciently s
%s=3;%number of windows where only noise
clearvars A;
mu=calculate_mu(B,s);
 

%% remove noise
 C = remove_noise(B,mu,s);
clearvars B;

%% ifft
for d = 1:length(C(:,1))
    Xhat_pieces(d,:) = ifft(C(d,:));
end
clearvars C;

%% add denoised windowed signals
Xhat = zeros(size(X));
for n = 1:length(Xhat_pieces(:,1))-1
     Xhat(start_of_window(n)+1:start_of_window(n)+256) = Xhat(start_of_window(n)+1:start_of_window(n)+256) + Xhat_pieces(n,:);
end

Xhat = real(Xhat);

end
