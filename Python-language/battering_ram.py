PRINTABLES_BEGIN = 32
PRINTABLES_END = 126

NUMBERS_BEGIN = 48
NUMBERS_END = 57

UPPER_CHARS_BEGIN = 65
UPPER_CHARS_END = 90

LOWER_CHARS_BEGIN = 97
LOWER_CHARS_END = 122

SYMBOLS_BEGIN_STEP1 = 32
SYMBOLS_END_STEP1 = 47

SYMBOLS_BEGIN_STEP2 = 58
SYMBOLS_END_STEP2 = 64

SYMBOLS_BEGIN_STEP3 = 91
SYMBOLS_END_STEP3 = 96

SYMBOLS_BEGIN_STEP4 = 123
SYMBOLS_END_STEP4 = 126


class battering_ram:
    __possible_chars = ""
    __buffer = ""
    __end_value = ""
    __upper_chars_enabled = False
    __lower_chars_enabled = False
    __numbers_enabled = False
    __symbols_enabled = False
    __initial_value_triggered = False
    __end_value_triggered = False

    def __insert_symbol_chars(self,BEGIN_OF_SECTION, END_OF_SECTION):
        i = BEGIN_OF_SECTION

        for x in range(END_OF_SECTION - BEGIN_OF_SECTION + 1):
            self.__possible_chars += chr(i)
            i += 1;
    

    def __init__(self,enable_upper_case,enable_lower_case,enable_symbols,enable_numbers) -> None:
        self.__numbers_enabled = enable_numbers
        self.__lower_chars_enabled = enable_lower_case
        self.__upper_chars_enabled = enable_upper_case
        self.__symbols_enabled = enable_symbols


        if(enable_numbers):
            i = NUMBERS_BEGIN
            j = 0

            while(j <= NUMBERS_END - NUMBERS_BEGIN):
                self.__possible_chars += chr(i)
                i += 1
                j += 1

        if(enable_upper_case):
            i = UPPER_CHARS_BEGIN
            j = 0
            while(j <= UPPER_CHARS_END - UPPER_CHARS_BEGIN):
                self.__possible_chars += chr(i)
                j += 1
                i += 1

        if(enable_lower_case):
            i = LOWER_CHARS_BEGIN
            j = 0
            while(j <= LOWER_CHARS_END - LOWER_CHARS_BEGIN):
                self.__possible_chars += chr(i)
                j += 1
                i += 1

        if(enable_symbols):
            self.__insert_symbol_chars(SYMBOLS_BEGIN_STEP1,SYMBOLS_END_STEP1)
            self.__insert_symbol_chars(SYMBOLS_BEGIN_STEP2,SYMBOLS_END_STEP2)
            self.__insert_symbol_chars(SYMBOLS_BEGIN_STEP3,SYMBOLS_END_STEP3)
            self.__insert_symbol_chars(SYMBOLS_BEGIN_STEP4,SYMBOLS_END_STEP4)
        self.__buffer = self.__possible_chars[0]
    
    def get_data(self):
        return self.__buffer

    def __reset_all_bytes(self):

        empty_string = ""
    
        char_to_use = self.__possible_chars[0]
        buffer_size = len(self.__buffer)

        for x in range(buffer_size):
            data = list(self.__buffer)
            data[x] = char_to_use

            self.__buffer = empty_string.join(data)

            empty_string = ""

    
    def __insert_char(self):
        char_to_use = self.__possible_chars[0]

        new_buffer = char_to_use
        new_buffer += self.__buffer
        self.__buffer = new_buffer


    def __get_next_char(self,current_char):

        next_char_position = self.__possible_chars.index(current_char) + 1
        

        if(next_char_position == len(self.__possible_chars)):
            current_char = self.__possible_chars[0]
            
            return (True,current_char)
        else:


            current_char = self.__possible_chars[next_char_position]
            
            return [False,current_char];
    
    def __is_the_max_possible_matches(self):
        buffer_size = len(self.__buffer)
        possible_chars_size = len(self.__possible_chars)

        is_the_end = True

        for x in range(buffer_size):
            if(self.__buffer[x] != self.__possible_chars[possible_chars_size - 1]):
                is_the_end = False
                break
        
        return is_the_end

    def get_next_sequence(self):
        if(self.__end_value_triggered and self.__buffer == self.__end_value):
            
            return False

        if(self.__is_the_max_possible_matches()):
            
            self.__reset_all_bytes()
            self.__insert_char()

        else:
            buffer_size = len(self.__buffer)
            current_char = self.__buffer[buffer_size - 1]

            carry_status_tuple = self.__get_next_char(current_char)

            empty_string = ""
        
            data = list(self.__buffer)

            data[buffer_size - 1] = carry_status_tuple[1]

            self.__buffer = empty_string.join(data)

            if(carry_status_tuple[0]):
                i =  buffer_size - 2
                while(i >= 0):
                    
            
                    empty_string = ""

                    current_char = self.__buffer[i]

                    carry_status_tuple = self.__get_next_char(current_char)
                    
                    data = list(self.__buffer)

                    data[i] = carry_status_tuple[1]

                    self.__buffer = empty_string.join(data)
                        
                    if(not carry_status_tuple[0]):
                        break

                    i -= 1
        return True
    def __check_allowed_chars(self,buffer):
        buffer_size = len(buffer)
        error_buffer = ""
        
        for x in range(buffer_size):
            if(buffer[x].isdigit()):
                if(not self.__numbers_enabled):
                    error_buffer = "numbers"

            if(buffer[x].islower()):
                if(not self.__lower_chars_enabled):
                    error_buffer = "lower chars"
            
            if(buffer[x].isupper()):
                if(not self.__upper_chars_enabled):
                    error_buffer = "upper chars"

        if(error_buffer != ""):
            print(f"Char array has not allowed chars ({error_buffer})")
            exit(1)
    def set_start_value(self,initial_value):
        self.__check_allowed_chars(initial_value)
        
        self.__initial_value_triggered = True
        self.__buffer = initial_value

    def set_end_value(self,end_value):
        self.__check_allowed_chars(end_value)
    
        self.__end_value_triggered = True

        self.__end_value = end_value

