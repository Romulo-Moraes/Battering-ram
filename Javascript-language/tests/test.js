const battering_ram = require("./../battering_ram").battering_ram;


let my_object = new battering_ram(false, false, true, false);

for (let i = 0; i <= 126; i++) {
  console.log(my_object.get_data());
  my_object.get_next_sequence();
}
