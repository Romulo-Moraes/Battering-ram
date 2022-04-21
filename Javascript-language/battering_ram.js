const PRINTABLES_BEGIN = 32
const PRINTABLES_END = 126

const NUMBERS_BEGIN = 48
const NUMBERS_END = 57

const UPPER_CHARS_BEGIN = 65
const UPPER_CHARS_END = 90

const LOWER_CHARS_BEGIN = 97
const LOWER_CHARS_END = 122

const SYMBOLS_BEGIN_STEP1 = 32
const SYMBOLS_BEGIN_END1 = 47

const SYMBOLS_BEGIN_STEP2 = 58
const SYMBOLS_BEGIN_END2 = 64

const SYMBOLS_BEGIN_STEP3 = 91
const SYMBOLS_BEGIN_END3 = 96

const SYMBOLS_BEGIN_STEP4 = 123
const SYMBOLS_BEGIN_END4 = 126

class not_allowed_chars extends Error { };

class battering_ram {


  #possible_chars = "";
  #buffer = "";
  #end_value = "";
  #upper_chars_enabled = false;
  #lower_chars_enabled = false;
  #numbers_enabled = false;
  #symbols_enabled = false;
  #initial_value_triggered = false;
  #end_value_triggered = false;

  constructor(enable_upper_case, enable_lower_case, enable_symbols, enable_numbers) {
    this.#numbers_enabled = enable_numbers;
    this.#lower_chars_enabled = enable_lower_case;
    this.#upper_chars_enabled = enable_upper_case;
    this.#symbols_enabled = enable_symbols;

    if (enable_numbers) {
      let i = NUMBERS_BEGIN;


      for (let j = 0; j <= NUMBERS_END - NUMBERS_BEGIN; j++) {
        this.#possible_chars += String.fromCharCode(i);
        i += 1;
      }
    }

    if (enable_upper_case) {
      let i = UPPER_CHARS_BEGIN;


      for (let j = 0; j <= UPPER_CHARS_END - UPPER_CHARS_BEGIN; j++) {
        this.#possible_chars += String.fromCharCode(i);
        i += 1;
      }
    }

    if (enable_lower_case) {
      let i = LOWER_CHARS_BEGIN;


      for (let j = 0; j <= LOWER_CHARS_END - LOWER_CHARS_BEGIN; j++) {
        this.#possible_chars += String.fromCharCode(i);

        i += 1;
      }
    }

    this.#buffer = this.#possible_chars[0];
  }

  get_data() {
    return this.#buffer;
  }

  #reset_all_bytes() {
    let new_string = "";

    let char_to_use = this.#possible_chars[0];
    let buffer_size = this.#buffer.length;

    for (let i = 0; i < buffer_size; i++) {
      new_string += char_to_use;
    }

    this.#buffer = new_string;
  }

  #insert_char() {
    let char_to_use = this.#possible_chars[0];

    let new_buffer = char_to_use;
    new_buffer += this.#buffer;

    this.#buffer = new_buffer;
  }

  #get_next_char(current_char) {
    let next_char_position = this.#possible_chars.indexOf(current_char) + 1;

    if (next_char_position == this.#possible_chars.length) {
      let current_char = this.#possible_chars[0];

      return [true, current_char];
    }
    else {
      let current_char = this.#possible_chars[next_char_position];

      return [false, current_char];
    }
  }

  #array_to_string(array) {
    let final_string = "";

    array.forEach(element => {
      final_string += element;
    });

    return final_string;
  }

  #is_the_max_possible_matches() {
    let buffer_size = this.#buffer.length;
    let possible_chars_size = this.#possible_chars.length;

    let is_the_end = true;

    for (let j = 0; j < buffer_size; j++) {
      if (this.#buffer[j] != this.#possible_chars[possible_chars_size - 1]) {
        is_the_end = false;
        break;
      }
    }

    return is_the_end;

  }
  get_next_sequence() {
    if (this.#end_value_triggered && this.#buffer == this.#end_value) {
      return false;
    }

    if (this.#is_the_max_possible_matches()) {

      this.#reset_all_bytes();
      this.#insert_char();

    }
    else {
      let buffer_size = this.#buffer.length;
      let current_char = this.#buffer[buffer_size - 1];

      let carry_status_tuple = this.#get_next_char(current_char);

      let data = Array.from(this.#buffer);

      data[buffer_size - 1] = carry_status_tuple[1];
      this.#buffer = this.#array_to_string(data);

      if (carry_status_tuple[0]) {
        let i = buffer_size - 2;

        for (let i = buffer_size - 2; i >= 0; i--) {
          current_char = this.#buffer[i];

          carry_status_tuple = this.#get_next_char(current_char);

          data = Array.from(this.#buffer);

          data[i] = carry_status_tuple[1];

          this.#buffer = this.#array_to_string(data);

          if (!carry_status_tuple[0]) {
            break;
          }
        }
      }
    }
    return true;
  }
  #check_allowed_chars(buffer) {
    let buffer_size = buffer.length;
    let error_buffer = "";

    let ascii = 0;
    for (let i = 0; i < buffer_size; i++) {
      ascii = buffer.charCodeAt(0);
      if (ascii >= NUMBERS_BEGIN && ascii <= NUMBERS_END) {
        if (!this.#numbers_enabled) {
          error_buffer = "numbers";
        }
      }

      if (ascii >= LOWER_CHARS_BEGIN && ascii <= LOWER_CHARS_END) {
        if (!this.#lower_chars_enabled) {
          error_buffer = "lower chars";
        }
      }

      if (ascii >= UPPER_CHARS_BEGIN && ascii <= UPPER_CHARS_END) {
        if (!this.#upper_chars_enabled) {
          error_buffer = "upper chars";
        }
      }

      if (error_buffer != "") {
        throw new not_allowed_chars(`Char array has not allowed chars (${error_buffer}`);
      }
    }
  }

  #set_start_value(initial_value) {
    this.#check_allowed_chars(initial_value);

    this.#initial_value_triggered = true;
    this.#buffer = initial_value;
  }

  #set_end_value(end_value) {
    this.#check_allowed_chars(end_value);

    this.#end_value_triggered = true;

    this.#end_value = end_value;
  }
}

module.exports = { battering_ram };
