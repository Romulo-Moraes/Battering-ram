function isdigit(char) {
  if (isNaN(Number(char))) {
    return false;
  }
  return true;
}

function isupper(char) {
  let ascii_representation = char.charCodeAt(0);

  if (ascii_representation >= 65 && ascii_representation <= 90 || ascii_representation >= 192 && ascii_representation <= 222) {
    return true;
  }

  return false;
}

function islower(char) {
  return char == char.toLowerCase()
}

console.log(islower('.'))


// console.log(isdigit("3"));
