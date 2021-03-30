/*
 * Write your client-side JS code in this file.  Don't forget to include your
 * name and @oregonstate.edu email address below.
 *
 * Name: Rudy Peralta
 * Email: peraltar@oregonstate.edu
 */

var sellingButton = document.getElementById("sell-something-button");
var shownClass = document.getElementsByClassName("hidden");
var modalCancel = document.getElementById("modal-cancel");
var modalClose = document.getElementById("modal-close");
var modalAccept = document.getElementById("modal-accept");
var sellModalInputList = document.getElementsByClassName("post-input-element");
var allPosts = document.querySelectorAll(".post");
var filterConditionList = [];
//var postCopy = [...allPosts].clone();

// --------------------------------------------




function toggleClassOn() {
    for (var i = 0; i < shownClass.length; i++) {
        shownClass[i].style.display = "block";
    }
}

function toggleClassOff() {
    for (var i = 0; i < shownClass.length; i++) {
        shownClass[i].style.display = "none";
    }
}

function clearModal() {
    for (var i = 0; i < sellModalInputList.length; i++) {
        sellModalInputList[i].lastElementChild.value = '';
    }
}

function elementToggleOnOff(element, onOffBool) {
    element.addEventListener("click", function() {
        if (onOffBool === true) {
            toggleClassOn();
        } else {
            toggleClassOff();
            clearModal();
        }
    });
}

function postCreate(price, city, condition, photoURL, itemDesc, hrefItemDesc) {
    if (price === '' || city === '' || condition === null || photoURL === '' || itemDesc === '' || hrefItemDesc === '') {
        alert("You need to fill out all of the fields please.");
    } else {
        var divPostContainer = document.createElement('div');
        var divPostContents = document.createElement('div');
        var divPostImgContainer = document.createElement('div');
        var image = document.createElement('img');
        var divPostInfoContainer = document.createElement('div');
        var aHrefTitle = document.createElement("a");
        var spanPostPrice = document.createElement('span');
        var spanPostCity = document.createElement('span');

        var sectionPosts = document.getElementById("posts");

        image.setAttribute("src", photoURL);
        image.setAttribute("alt", itemDesc);
        divPostImgContainer.appendChild(image);
        divPostContainer.classList.add("post");
        divPostContainer.setAttribute("data-price", price);
        divPostContainer.setAttribute("data-city", city);
        divPostContainer.setAttribute("data-condition", condition);
        divPostContents.classList.add("post-contents");
        divPostImgContainer.classList.add("post-image-container");
        divPostInfoContainer.classList.add("post-info-container");
        // ---------------------------------------
        aHrefTitle.setAttribute("href", "#");
        divPostInfoContainer.appendChild(aHrefTitle);
        aHrefTitle.classList.add("post-title");
        aHrefTitle.textContent = hrefItemDesc;
        spanPostPrice.classList.add("post-price");
        spanPostPrice.textContent = " $" + price + " ";
        spanPostCity.classList.add("post-city");
        spanPostCity.textContent = " (" + city + ") ";
        // ---------------------------------------
        divPostContents.appendChild(divPostImgContainer);
        divPostContents.appendChild(divPostInfoContainer);
        sectionPosts.appendChild(divPostContainer);
        divPostContainer.appendChild(divPostContents);
        divPostInfoContainer.appendChild(spanPostPrice);
        divPostInfoContainer.appendChild(spanPostCity);
        toggleClassOff();
        clearModal();
    }
}


function modalAcceptButton() {
    var postText = document.getElementById("post-text-input");
    var postPhotoURL = document.getElementById("post-photo-input");
    var postPriceInput = document.getElementById("post-price-input");
    var postCityInput = document.getElementById("post-city-input")
    var postConditionField = document.getElementById("post-condition-fieldset");
    var modalAcceptButton = document.getElementById("modal-accept");

    modalAcceptButton.addEventListener("click", function() {
        postCreate(postPriceInput.value, postCityInput.value, postConditionField.value, postPhotoURL.value, postText.value, postText.value);
    });
}

function deletePost(postElement, name, price, city, condition, filterText, filterMinPrice, filterMaxPrice, filterCityText, filterConditionArr) { // This is gonna take an element from a nodelist and delete it.
    // Don't need to worry about nothing being there.




    console.log("Filter Text:\n\t" + filterText);
    console.log("Filter Check: " + name.toLowerCase().includes(filterText.toLowerCase()));
    if (filterText.toLowerCase() !== '' && !name.toLowerCase().includes(filterText.toLowerCase())) {
        postElement.remove();
    }
    // console.log("Min and Max Price Filter T/F:\n\t" + "Post Price: " + price + "\n\tMin Filter Price: " + filterMinPrice + "\n\t" + "Max Filter Price: " + filterMaxPrice);

    if (filterMinPrice !== '' && !(filterMinPrice <= parseInt(price))) {
        postElement.remove();
    }
    if (filterMaxPrice !== '' && !(parseInt(price) <= filterMaxPrice)) {
        postElement.remove();
    }
    if (filterConditionArr.length !== 0 && !filterConditionArr.includes(condition)) { // If the filter exists here it's good and doesn't get deleted.
        postElement.remove();
    }
    console.log("Filtered City: " + filterCityText + " city: " + city);
    if (filterCityText !== "any" && city !== filterCityText) {
        postElement.remove();
    }
}


function filter() {

    var filterConditions = document.querySelectorAll("#filter-condition input:checked"); // Currently a nodelist.
    for (var i = 0; i < filterConditions.length; i++) {
        filterConditionList.push(filterConditions[i].value);
    }
    //for(const checkedFields in 
    console.log(filterConditionList);
    for (var i = allPosts.length - 1; i >= 0; i--) {
        var postQuery = document.querySelectorAll(".post");
        var filterCityDropdown = document.getElementById("filter-city");
        // var filterCheckbox = document.querySelector("#filter-condition input:checked");

        var nameStr = postQuery[i].firstElementChild.lastElementChild.getElementsByTagName("a")[0].text.toLowerCase(); // This gets the name of the damn thing, I wanna cry on the inside. This took too long, and I want my time back, where's JJ Wentworth when I need cash now?!
        var price = postQuery[i].dataset.price;
        var city = postQuery[i].dataset.city;
        var condition = postQuery[i].dataset.condition;

        var filterText = document.getElementById("filter-text").value.toLowerCase();
        var filterMinPrice = document.getElementById("filter-min-price").value;
        var filterMaxPrice = document.getElementById("filter-max-price").value;
        var filterCityText = filterCityDropdown.options[filterCityDropdown.selectedIndex].text;

        if (filterText === "" && (filterMinPrice === '' || filterMaxPrice == '') && filterCityText === "") { // This checks for a completely empty filter.
            console.log("Empty Query");
        } else { // If the text isn't empty, and the other filters exist
            deletePost(postQuery[i], nameStr, price, city.toLowerCase(), condition, filterText, filterMinPrice, filterMaxPrice, filterCityText.toLowerCase(), filterConditionList);
        }



        console.log("Name: " + nameStr + " \nPrice: " + price + " \nCity: " + city + " \nCondition: " + condition + " \nFilter Text: " + filterText + " \nFilter Min Price: " + filterMinPrice + " \nFilter Max Price: " + filterMaxPrice + " \nFilter City Text: " + filterCityText + "\n ----------------------------- ");

    }
}

function filterButton() {
    var filterUpdateButton = document.getElementById("filter-update-button");
    filterUpdateButton.addEventListener("click", function() {
        /* By the way, the thing you were working on last was adding an event listener []
         you did it btw. The next thing on the list is using all the data that we have and then removing posts from there
         so tomorrow morning, start working on a removal method and then cross reference everything from there. 77
        */

        filter();

    });
}

elementToggleOnOff(sellingButton, true);
elementToggleOnOff(modalCancel, false);
elementToggleOnOff(modalClose, false);
modalAcceptButton();
filter();
filterButton();