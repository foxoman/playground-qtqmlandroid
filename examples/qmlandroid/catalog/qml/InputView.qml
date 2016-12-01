import android.widget 0.21
import android.support.v7.widget 0.21

ScrollView {
    LinearLayout {
        padding: 48
        orientation: LinearLayout.VERTICAL

        CardView {
            LinearLayout {
                padding: 48
                orientation: LinearLayout.VERTICAL

                TextView { text: "EditText (single line)"; textSize: 18 }
                Space { LinearLayout.height: 48 }
                EditText {
                    hint: "Username"
                    singleLine: true
                }
                Space { LinearLayout.height: 48 }
                EditText {
                    hint: "Password"
                    singleLine: true
                    inputType: 1 | 128 // TODO: TYPE_CLASS_TEXT | TYPE_TEXT_VARIATION_VISIBLE_PASSWORD
                }
            }
        }

        Space { LinearLayout.height: 48 }

        CardView {
            LinearLayout {
                padding: 48
                orientation: LinearLayout.VERTICAL

                TextView { text: "EditText (multi-line)"; textSize: 18 }
                Space { LinearLayout.height: 48 }
                EditText {
                    text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer feugiat purus urna, in feugiat diam pulvinar non. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Interdum et malesuada fames ac ante ipsum primis in faucibus."
                }
            }
        }

        Space { LinearLayout.height: 48 }

        CardView {
            LinearLayout {
                padding: 48
                orientation: LinearLayout.VERTICAL

                TextView { text: "Spinner"; textSize: 18 }
                Space { LinearLayout.height: 48 }
                Spinner {
                    adapter: ArrayAdapter {
                        array: ["Apple", "Banana", "Orange"]
                    }
                }
            }
        }
    }
}
