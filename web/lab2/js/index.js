function changeTextLength(length) {
    const textField = document.querySelector(".left p");
    switch (length) {
        case "short_text":
            textField.innerHTML =
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
            break;
        case "long_text":
            textField.innerHTML =
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." +
                "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat." +
                "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur." +
                "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
            break;
    }
}

function changeImage(image) {
    const imageElement = document.querySelector(".right img");
    imageElement.src = "assets/images/" + image;
}

(function(){
    const textLengthInput = document.querySelector("#text_length_input");
    textLengthInput.addEventListener("change", (event) => {
        changeTextLength(textLengthInput.value);
    });
    changeTextLength(textLengthInput.value);

    const imageInput = document.querySelector("#image_input");
    imageInput.addEventListener("change", (event) => {
        changeImage(imageInput.value);
    });
    changeImage(imageInput.value);
})();
