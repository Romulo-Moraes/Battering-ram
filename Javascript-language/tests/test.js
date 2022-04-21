const battering_ram = require("./../battering_ram").battering_ram;

let my_object = new battering_ram(false, false, false, true);

let current_data = "";

let store_interval = setInterval(() => {

  current_data = my_object.get_data();
  if (current_data == "rOmU") {
    console.log("Gotcha!");
    clearInterval(store_interval);
  }
  else {
    console.log(current_data);
  }
  my_object.get_next_sequence();

}, 500);

