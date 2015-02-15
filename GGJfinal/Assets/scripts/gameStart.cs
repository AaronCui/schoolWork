using UnityEngine;
using System.Collections;

public class gameStart : MonoBehaviour {

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if( Input.GetMouseButtonDown(0) ){
			//Left Click
			Ray click = Camera.main.ScreenPointToRay(Input.mousePosition);
			RaycastHit hit;
			Physics.Raycast(click, out hit);
				if( hit.collider ){
					moveToFirstScene();
				}
		}


	}


	void moveToFirstScene(){
		Application.LoadLevel(1);
	}
}
