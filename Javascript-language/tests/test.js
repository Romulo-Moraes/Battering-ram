const battering_ram = require("./../battering_ram").battering_ram;

let my_object = new battering_ram(true, true, false, false);

let current_data = "";

do {
  current_data = my_object.get_data();
  if (current_data == "rOmU") {
    console.log("Gotcha!");
    break;
  }
  else {
    console.log(current_data);
  }
} while (my_object.get_next_sequence());
