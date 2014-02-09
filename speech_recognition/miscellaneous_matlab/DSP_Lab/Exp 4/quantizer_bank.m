function Q = quantizer_bank(Y,number_of_levels)

% assume number of levels = 4
size_size = size(Y);
size_size(2) = ceil(size_size(2)/32);
Q = zeros(size_size);

for n = 1:size_size(1)
    % normalize each row so that the values are between 0 and 1
    scale_factor = max(Y(n,:));
    Y(n,:) = Y(n,:)/scale_factor;
   
    % quantize
    for iterator = 1:length(Y(n,:))
        
        % if the signal value is very small
        lowest_level = (2/number_of_levels) - 1;
        if (Y(n,iterator) < lowest_level)
            Q(n,iterator) = lowest_level;
            
        else
            % middle case: if the signal value is in one of the intermediate
            % levels
            for i = 1:number_of_levels
                level = (i*2/number_of_levels) - 1;
         
                if ((Y(n,iterator) > level) && (Y(n,iterator) < level+2/number_of_levels))
                    Q(n,iterator) = level;
                elseif((Y(n,iterator) > level))
                    Q(n,iterator) = level+2/number_of_levels;
                end
            end
        end
    end
    
    Q(n,:) = Q(n,:)*scale_factor;
end
end