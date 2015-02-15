
using UnityEngine;
using System.Collections;

public class wormhole : MonoBehaviour {
	
	private GameObject director;
	private GameObject player;
	private GameObject[] wormholes;

	public bool side;
	public int set;

	private Vector3 nextPosition; 
	//public float mass;
	
	//public bool holeside;
	//public int setid;

	
	// Use this for initialization
	void Start () {
		//Debug.Log ();
		director = GameObject.FindGameObjectWithTag ("Director");
		player = director.GetComponent<GameDirector>().player;
		wormholes = director.GetComponent<GameDirector>().wormholes;
		for(int i=0; i< wormholes.Length ; i++) {
			if (wormholes[i].GetComponent<wormhole>().set == this.set && wormholes[i].GetComponent<wormhole>().side != this.side){
				nextPosition = wormholes[i].GetComponent<wormhole>().transform.position; 
				break;
			}
		}
	}
	
	// Update is called once per frame
	void Update () {
		Debug.Log (0);
	}
	
	void OnTriggerEnter(Collider col){
		Debug.Log(col.transform.position);
		col.transform.position = nextPosition + col.transform.forward*2;  // change the scale to make sense 
	}	
}
	
	
