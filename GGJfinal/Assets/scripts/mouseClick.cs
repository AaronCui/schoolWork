using UnityEngine;
using System.Collections;

public class mouseClick : MonoBehaviour {

	private RaycastHit hit;
	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if( Input.GetMouseButtonDown(0) ){
			//Left Click
			Ray click = Camera.main.ScreenPointToRay(Input.mousePosition);
			hit = rayHit (click);
			if( hit.collider ){
				//hit
				switch( hit.collider.tag ){
				case "planet" :	hit.collider.GetComponent<planet>().increaseMass (); break;
				case "player" : hit.collider.GetComponent<playerBehavior>().velocity *= (0.3f); break;
				case "asteroid" : hit.collider.GetComponent<asteroid>().OnExplode(); break;
				case "magnet" : hit.collider.GetComponent<magnet>().magnetOn(); break;
				default : break;
				}
			}
		}else if(Input.GetMouseButtonDown(1) ){
			//Right Click
			Ray click = Camera.main.ScreenPointToRay(Input.mousePosition);
			hit = rayHit (click);
			if( hit.collider ){
				//hit
				switch( hit.collider.tag ){
				case "planet" :	hit.collider.GetComponent<planet>().decreaseMass (); break;
				default : break;
				}
		
	  		}
		}
	}


	RaycastHit rayHit(Ray _click){
		RaycastHit _hit;
		Physics.Raycast(_click, out _hit);
		return _hit;
	}
}
