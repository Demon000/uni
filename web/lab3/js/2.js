function findLabelForInput(input) {
    return document.querySelector(`label[for="${input.id}"]`);
}

function getInputElementNames(inputs) {
    const names = [];
    for (const input of inputs) {
        const label = findLabelForInput(input);
        names.push(label.textContent);
    }

    return names;
}

function calculateAge(birthday) {
    const ageDifMs = Date.now() - birthday.getTime();
    const ageDate = new Date(ageDifMs);
    return Math.abs(ageDate.getUTCFullYear() - 1970);
}

function setInputElementValidity(inputElement, isValid) {
    if (isValid) {
        inputElement.classList.remove("invalid");
    } else {
        inputElement.classList.add("invalid");
    }
}

function updateInputElementsValidity(form) {
    const inputElements = form.querySelectorAll("input");
    const invalidInputElements = [];
    for (const inputElement of inputElements) {
        const isValid = inputElement.validity.valid;
        setInputElementValidity(inputElement, isValid);
        if (!isValid) {
            invalidInputElements.push(inputElement);
        }
    }

    return invalidInputElements;
}

function concatInputElementNames(names) {
    return names.map(name => name.toLowerCase()).join(", ");
}

(function() {
    const registrationForm = document.querySelector("#registration-form");
    const submitButton = document.querySelector("#registration-form-submit");
    const birthDateInput = document.querySelector("#registration-form-birth-date");
    const ageInput = document.querySelector("#registration-form-age");
    const validitySuccessElement = document.querySelector("#registration-form-validity-success");
    const validityFailElement = document.querySelector("#registration-form-validity-fail");
    const validityFailFieldsElement = document.querySelector("#registration-form-fail-fields");

    submitButton.addEventListener("click", () => {
        const invalidInputElements = updateInputElementsValidity(registrationForm);

        if (!invalidInputElements.includes(ageInput)) {
            const birthDate = new Date(birthDateInput.value);
            const age = +ageInput.value;
            if (calculateAge(birthDate) !== age) {
                invalidInputElements.push(ageInput);
                setInputElementValidity(ageInput, false);
            }
        }

        if (invalidInputElements.length === 0) {
            validitySuccessElement.classList.add("visible");
            validityFailElement.classList.remove("visible");
        } else {
            validitySuccessElement.classList.remove("visible");
            validityFailElement.classList.add("visible");
            const names = getInputElementNames(invalidInputElements);
            validityFailFieldsElement.innerHTML = concatInputElementNames(names);
        }
    });
})();