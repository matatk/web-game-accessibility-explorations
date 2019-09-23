'use strict'
let liveRegion

mergeInto(LibraryManager.library, {
	screen_reader_setup: function() {
		const liveRegionHeading = document.createElement('H1')
		liveRegionHeading.style.padding = '0.5rem'
		liveRegionHeading.innerText = 'Live region (the below will be announced by a screen-reader)'
		document.body.appendChild(liveRegionHeading)
		liveRegion = document.createElement('DIV')
		liveRegion.style.margin = '0.5rem'
		liveRegion.style.padding = '0.5rem'
		liveRegion.style.border = '0.1rem solid black'
		liveRegion.setAttribute('aria-live', 'assertive')
		document.body.appendChild(liveRegion)
	},

	screen_reader_announce: function(message) {
		liveRegion.innerText = UTF8ToString(message, 128)
	},
})
