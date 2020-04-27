function findLabelForInput(input) {
    return $(`label[for="${input.attr("id")}"]`);
}

function getInputElementNames(inputs) {
    const names = [];
    for (const input of inputs) {
        const label = findLabelForInput(input);
        names.push(label.text());
    }

    return names;
}

function calculateAge(birthday) {
    const ageDifMs = Date.now() - birthday.getTime();
    const ageDate = new Date(ageDifMs);
    return Math.abs(ageDate.getUTCFullYear() - 1970);
}

function setInputElementValidity(inputElement, isValid) {
    inputElement.toggleClass("invalid", !isValid);
}

function updateInputElementsValidity(form) {
    const inputElements = form.find("input");
    const invalidInputElements = [];
    inputElements.each((_, _inputElement) => {
        const inputElement = $(_inputElement);
        const isValid = _inputElement.validity.valid;
        setInputElementValidity(inputElement, isValid);
        if (!isValid) {
            invalidInputElements.push(inputElement);
        }
    });

    return invalidInputElements;
}

function concatInputElementNames(names) {
    return names.map(name => name.toLowerCase()).join(", ");
}

(function() {
    const registrationForm = $("#registration-form");
    const submitButton = $("#registration-form-submit");
    const nameInput = $("#registration-form-name");
    const birthDateInput = $("#registration-form-birth-date");
    const ageInput = $("#registration-form-age");
    const validitySuccessElement = $("#registration-form-validity-success");
    const validityFailElement = $("#registration-form-validity-fail");
    const validityFailFieldsElement = $("#registration-form-fail-fields");

    submitButton.click(() => {
        const invalidInputElements = updateInputElementsValidity(registrationForm);

        if (!invalidInputElements.includes(ageInput)) {
            const birthDate = new Date(birthDateInput.val());
            const age = +ageInput.val();
            if (calculateAge(birthDate) !== age) {
                invalidInputElements.push(ageInput);
                setInputElementValidity(ageInput, false);
            }
        }

        if  (!invalidInputElements.includes(nameInput)) {
            const name = nameInput.val();
            if (!/^[A-Za-z -]+$/.test(name)) {
                invalidInputElements.push(nameInput);
                setInputElementValidity(nameInput, false);
            }
        }

        const isAllValid = invalidInputElements.length === 0;
        validitySuccessElement.toggleClass("visible", isAllValid);
        validityFailElement.toggleClass("visible",!isAllValid);
        if (!isAllValid) {
            const names = getInputElementNames(invalidInputElements);
            console.log(names);
            validityFailFieldsElement.text(concatInputElementNames(names));
        }
    });
})();
