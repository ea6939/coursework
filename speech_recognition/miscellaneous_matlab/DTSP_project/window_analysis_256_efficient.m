function result256 = window_analysis_256_efficient(X,overlap)

T0 = 256;
input_signal_length = length(X);

number_of_windows = (input_signal_length/T0)*(1+overlap);
start_of_window = (input_signal_length/number_of_windows)*(0:number_of_windows-1);

for i=1:number_of_windows-2
    offset = 1;
    
    Wprime = w(-start_of_window(i)-T0/2,T0+1,input_signal_length);
    suffix = zeros(1,input_signal_length-length(Wprime));
    W = [Wprime suffix];
    
    result = W(1:input_signal_length).*X;
    interval_start = start_of_window(i)+1;
    interval_end = (start_of_window(i)+255)+1;
    
    if (interval_end > length(X))
        interval_end = length(X);
    end
    
result256(i,:) = result(1,interval_start:interval_end);
    
end

% scale_factor = 3.9 / 3;
% result256 = result256 / scale_factor;


end