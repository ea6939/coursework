function result = choose_starting_window(input_signal_length,number_of_windows,start_sample)

size=0;
window=1;
for d = 1:number_of_windows
    if(size<start_sample)
    size=size+(input_signal_length/number_of_windows);
    window=window+1;
    end
end


result=window;