using UnityEngine;
using System.Collections;

public class Factory : MonoBehaviour {

	public GameObject bullet;
	public GameObject dynamicBullet;
	public GameObject magnet;
	public GameObject item;

	public int totalOnce;
	public int totalOnceAst;

	private int itemTotal = 1;
	private int magnetTotal = 1;

	private GameObject director;
	private GameObject player;
	private Vector3 towardPlayer;

	private float factoryBound = 10.0f;
	private GameObject [] bulletSet;
	private GameObject [] bulletDy;
	private GameObject [] items;
	private GameObject magnetBullet;


	private float timer;

	private float dist = 4.0f;
	private float wing = 10.0f;

	// Use this for initialization
	void Start () {
		timer = 0;
		director = GameObject.FindGameObjectWithTag("Director");
		player = director.GetComponent<GameDirector>().player;
		towardPlayer = Vector3.Normalize ( transform.position - player.transform.position ); 

		bulletSet = new GameObject[totalOnce];
		bulletDy = new GameObject[totalOnceAst];
	}
	
	// Update is called once per frame
	void Update () {
		timer += Time.deltaTime;
		towardPlayer = Vector3.Normalize ( transform.position - player.transform.position ); 

		if ( timer >= 6 ){
			timer = 0;
			//destroyOut ();
			createIn ();
			throwBullets();
			loadMagnet();
			loadItems ();
		}

	}

	void destroyOut(){
		for ( int i = 0; i < totalOnce; i++ ){
			Destroy(bulletSet[i]);
		}
	}

	void createIn(){

		for( int i = 0; i < totalOnce; i++ ){
			bulletSet[i] = (GameObject) Instantiate(bullet, 
			                                        player.transform.position + 
			                                        new Vector3( Random.Range (-factoryBound, factoryBound),
			            									     Random.Range (-factoryBound, factoryBound), 0.0f),
			                                        transform.localRotation);
			bulletSet[i].rigidbody.AddForce (
				Vector3.Normalize(bulletSet[i].transform.position - player.transform.position)*30 );

		}
	}


	void throwBullets(){
	
		Vector3 criticPoint = player.transform.position + (player.transform.forward)*dist;
		Vector3 leftWing = new Vector3 ( (-1.0f)*(player.transform.position.y), player.transform.position.x, 0.0f);
		float tmpLength = 0.0f;

		for ( int i = 0; i < totalOnceAst; i++ ){
			tmpLength = Random.Range (-wing, wing);
			bulletDy[i] = (GameObject) Instantiate (dynamicBullet, criticPoint + leftWing*tmpLength, transform.localRotation);
			bulletDy[i].GetComponent<asteroid>().setForward(player);
		}

	}

	void loadMagnet(){
		magnetBullet = (GameObject) Instantiate (magnet, player.transform.position + 
		                                         new Vector3( Random.Range (-factoryBound, factoryBound),
		          								  Random.Range (-factoryBound, factoryBound), 0.0f),
		                                         transform.localRotation);
	}

	void loadItems(){
		for( int i = 0; i < itemTotal; i++ ){
			items[i] = (GameObject) Instantiate(item, 
			                                        player.transform.position + 
			                                        new Vector3( Random.Range (-factoryBound, factoryBound),
			            Random.Range (-factoryBound, factoryBound), 0.0f),
			                                        transform.localRotation);
			items[i].rigidbody.AddForce (
				Vector3.Normalize(items[i].transform.position - player.transform.position)*30 );
			
		}
	}

}
